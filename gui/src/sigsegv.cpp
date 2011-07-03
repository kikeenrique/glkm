/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.cpp
 * Author: Jaco Kroon <jaco@kroon.co.za>
 * Copyright (C) 2005 - 2009 Jaco Kroon
 * Copyright (C) Enrique García Álvarez 2007 <kike+glkm@eldemonionegro.com>
 *
 * gui is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * gui is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

/**
 * This source file is used to print out a stack-trace when your program
 * segfaults. It is relatively reliable and spot-on accurate.
 *
 * This code is in the public domain. Use it as you see fit, some credit
 * would be appreciated, but is not a prerequisite for usage. Feedback
 * on it's use would encourage further development and maintenance.
 *
 * Due to a bug in gcc-4.x.x you currently have to compile as C++ if you want
 * demangling to work.
 *
 * Please note that it's been ported into my ULS library, thus the check for
 * HAS_ULSLIB and the use of the sigsegv_outp macro based on that define.
 */

/* Bug in gcc prevents from using CPP_DEMANGLE in pure "C" */
#if !defined(__cplusplus) && !defined(NO_CPP_DEMANGLE)
        #define NO_CPP_DEMANGLE
#endif

#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <ucontext.h>
#include <dlfcn.h>
#ifndef NO_CPP_DEMANGLE
        #include <cxxabi.h>
        #ifdef __cplusplus
                using __cxxabiv1::__cxa_demangle;
        #endif
#endif

#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


#define sigsegv_outp(x, ...)    fprintf(stderr, x "\n", ##__VA_ARGS__)

#if defined(REG_RIP)
        # define SIGSEGV_STACK_IA64
        # define REGFORMAT "%016lx"
#elif defined(REG_EIP)
        # define SIGSEGV_STACK_X86
        # define REGFORMAT "%08x"
#else
        # define SIGSEGV_STACK_GENERIC
        # define REGFORMAT "%x"
#endif

static void signal_segv(int signum, siginfo_t* info, void*ptr) {
    static const char *si_codes[3] = {"", "SEGV_MAPERR", "SEGV_ACCERR"};

    int i, f = 0;
    ucontext_t *ucontext = (ucontext_t*)ptr;
    Dl_info dlinfo;
    void **bp = 0;
    void *ip = 0;

    sigsegv_outp("Segmentation Fault!");
    sigsegv_outp("info.si_signo = %d", signum);
    sigsegv_outp("info.si_errno = %d", info->si_errno);
    sigsegv_outp("info.si_code  = %d (%s)", info->si_code, si_codes[info->si_code]);
    sigsegv_outp("info.si_addr  = %p", info->si_addr);
    for (i = 0; i < NGREG; i++)
        sigsegv_outp("reg[%02d]       = 0x" REGFORMAT, i, ucontext->uc_mcontext.gregs[i]);

#ifndef SIGSEGV_NOSTACK
#if defined(SIGSEGV_STACK_IA64) || defined(SIGSEGV_STACK_X86)
#if defined(SIGSEGV_STACK_IA64)
    ip = (void*)ucontext->uc_mcontext.gregs[REG_RIP];
    bp = (void**)ucontext->uc_mcontext.gregs[REG_RBP];
#elif defined(SIGSEGV_STACK_X86)
    ip = (void*)ucontext->uc_mcontext.gregs[REG_EIP];
    bp = (void**)ucontext->uc_mcontext.gregs[REG_EBP];
#endif

    sigsegv_outp("Stack trace:");
    while (bp && ip) {
        if (!dladdr(ip, &dlinfo))
            break;

        const char *symname = dlinfo.dli_sname;

#ifndef NO_CPP_DEMANGLE
        int status;
        char * tmp = __cxa_demangle(symname, NULL, 0, &status);

        if (status == 0 && tmp)
            symname = tmp;
#endif

        sigsegv_outp("% 2d: %p <%s+%lu> (%s)",
                     ++f,
                     ip,
                     symname,
                     (unsigned long)ip - (unsigned long)dlinfo.dli_saddr,
                     dlinfo.dli_fname);

#ifndef NO_CPP_DEMANGLE
        if (tmp)
            free(tmp);
#endif

        if (dlinfo.dli_sname && !strcmp(dlinfo.dli_sname, "main"))
            break;

        ip = bp[1];
        bp = (void**)bp[0];
    }
#else
    sigsegv_outp("Stack trace (non-dedicated):");
    sz = backtrace(bt, 20);
    strings = backtrace_symbols(bt, sz);
    for (i = 0; i < sz; ++i)
        sigsegv_outp("%s", strings[i]);
#endif
    sigsegv_outp("End of stack trace.");
#else
    sigsegv_outp("Not printing stack strace.");
#endif
    _exit (-1);
}

/* Obtain a backtrace and print it to stdout. */
void print_trace (void)
{
    void *array[30];
    size_t size;
    char **strings;
    size_t i;

    size = backtrace (array, 30);
    strings = backtrace_symbols (array, size);

    printf ("Obtained %zd stack frames.\n", size);

    for (i = 0; i < size; i++)
        printf ("%s\n", strings[i]);

    free (strings);
    _exit (-1);
}


//#include <cxxabi.h>
//#include <execinfo.h>
//https://tombarta.wordpress.com/2008/08/01/c-stack-traces-with-gcc/
//void print_trace_2_0(FILE *out, const char *file, int line)
void print_trace_2_0(int,siginfo_t*, void*)
{
    const size_t max_depth = 100;
    size_t stack_depth;
    void *stack_addrs[max_depth];
    char **stack_strings;

    stack_depth = backtrace(stack_addrs, max_depth);
    stack_strings = backtrace_symbols(stack_addrs, stack_depth);

    std::cout << "Call stack" << std::endl;
//     fprintf(out, "Call stack from %s:%d:\n", file, line);

    for (size_t i = 1; i < stack_depth; i++) {
        size_t sz = 200; // just a guess, template names will go much wider
        char *function = static_cast<char*>(malloc(sz));
        char *begin = 0, *end = 0;
        // find the parentheses and address offset surrounding the mangled name
        for (char *j = stack_strings[i]; *j; ++j) {
            if (*j == '(') {
                begin = j;
            }
            else if (*j == '+') {
                end = j;
            }
        }
        if (begin && end) {
            *begin++ = ' ';
            *end = ' ';
            // found our mangled name, now in [begin, end)

            int status;
            char *ret = abi::__cxa_demangle(begin, function, &sz, &status);
            if (ret) {
                // return value may be a realloc() of the input
                function = ret;
            }
            else {
                // demangling failed, just pretend it's a C function with no args
                strncpy(function, begin, sz);
                strncat(function, "()", sz);
                function[sz-1] = ' ';
            }
            std::cout << "    " << stack_strings[i] << function << std::endl;
//             fprintf(out, "    %s:%s\n", stack_strings[i], function);
        }
        else
        {
            // didn't find the mangled name, just print the whole line
            std::cout << "    " << stack_strings[i] << std::endl;
//             fprintf(out, "    %s\n", stack_strings[i]);
        }
        free(function);
    }
    free(stack_strings); // malloc()ed by backtrace_symbols
    std::cout.flush();
//     fflush(out);
}


static void __attribute__((constructor)) setup_sigsegv() {
    struct sigaction action;
    memset(&action, 0, sizeof(action));
  action.sa_sigaction = signal_segv;
//     action.sa_sigaction =  print_trace_2_0;
    action.sa_flags = SA_SIGINFO;
    if (sigaction(SIGSEGV, &action, NULL) < 0)
        perror("sigaction");
}


