format 56

classinstance 128008 class_ref 128092 // MainWindow
  name ""   xyz 49 5 2000 life_line_z 2000
classinstancecanvas 129032 classinstance_ref 128008 // _pIconViewHosts
  xyz 348 4 2005 life_line_z 2000
classinstancecanvas 129288 classinstance_ref 128264 // _pHostSelectDialog
  xyz 144 4 2000 life_line_z 2000
classinstancecanvas 132872 classinstance_ref 129672 // _pHosts
  xyz 771 232 2000 life_line_z 2010
note 133256 "HostSelectDialogAtribute"
  xyzwh 259 60 2000 157 35
classinstancecanvas 133768 classinstance_ref 130824 // s
  xyz 563 226 2000 life_line_z 2010
fragment 136200 "alt"
  xyzwh 764 467 0 895 534
end
classinstance 136328 class_ref 128121 // Host
  name "_hosts[hostname]"   xyz 879 522 2000 life_line_z 2000
textcanvas 136712 "find() == _hosts.end()"
  xyzwh 780 489 2020 116 23
note 138120 "if hostname is not registered"
  xyzwh 662 500 2025 75 60
classinstancecanvas 138376 classinstance_ref 131976 // _pNotebooHosts
  xyz 1009 521 2000 life_line_z 2000
classinstancecanvas 140168 classinstance_ref 132104 // _refPtrGlademmXml2
  mortal  xyz 1167 638 2005 life_line_z 2000
note 140552 "	_refPtrGlademmXml2->create(GLADE_FILE, NotebookHostroot)
bouml doesn't know how to represent this"
  xyzwh 1314 766 2020 330 45
note 141320 "_refPtrGlademmXml2->get_widget_derived(\"notebook_hosts-hpaned\", tmp);"
  xyzwh 1313 822 2000 329 46
classinstancecanvas 141576 classinstance_ref 132232 // *tmp
  xyz 1365 637 2000 life_line_z 2000
note 145800 "NotebookPageHost will be a subcontainer of NotebookHosts"
  xyzwh 1143 558 2005 172 50
note 154760 "//TODO
//Set direct access on tree*view*host to host
We can call it conect them
"
  xyzwh 849 991 2000 349 177
durationcanvas 128136 classinstance_ref 128008 // :MainWindow
  xyzwh 80 65 2010 11 71
end
durationcanvas 129800 classinstance_ref 129288 // _pHostSelectDialog:HostSelectDialog
  xyzwh 231 104 2010 11 27
end
durationcanvas 130568 classinstance_ref 129288 // _pHostSelectDialog:HostSelectDialog
  xyzwh 231 235 2010 11 829
  overlappingdurationcanvas 130824
    xyzwh 237 1025 2020 11 25
  end
end
durationcanvas 131848 classinstance_ref 129032 // _pIconViewHosts:IconViewHosts
  xyzwh 425 169 2010 11 35
end
durationcanvas 133896 classinstance_ref 133768 // s:Controller
  xyzwh 590 291 2015 11 710
end
durationcanvas 135304 classinstance_ref 129032 // _pIconViewHosts:IconViewHosts
  xyzwh 425 340 2010 11 56
end
durationcanvas 135688 classinstance_ref 132872 // _pHosts:Hosts
  xyzwh 806 346 2015 11 650
  overlappingdurationcanvas 135944
    xyzwh 812 433 2020 11 31
  end
  overlappingdurationcanvas 151304
    xyzwh 812 770 2025 11 35
  end
end
durationcanvas 136456 classinstance_ref 136328 // _hosts[hostname]:Host
  xyzwh 933 600 2010 11 31
end
durationcanvas 137096 classinstance_ref 136328 // _hosts[hostname]:Host
  xyzwh 933 641 2010 11 25
end
durationcanvas 137352 classinstance_ref 136328 // _hosts[hostname]:Host
  xyzwh 933 676 2010 11 25
end
durationcanvas 137608 classinstance_ref 136328 // _hosts[hostname]:Host
  xyzwh 933 715 2010 11 26
end
durationcanvas 152072 classinstance_ref 138376 // _pNotebooHosts:NotebookHosts
  xyzwh 1088 785 2010 11 196
  overlappingdurationcanvas 152328
    xyzwh 1094 798 2020 11 177
    overlappingdurationcanvas 153096
      xyzwh 1100 916 2030 11 25
    end
    overlappingdurationcanvas 153352
      xyzwh 1100 945 2030 11 25
    end
  end
end
durationcanvas 153608 classinstance_ref 140168 // _refPtrGlademmXml2:RefPtrGladeXml
  xyzwh 1255 821 2010 11 25
end
durationcanvas 153864 classinstance_ref 140168 // _refPtrGlademmXml2:RefPtrGladeXml
  xyzwh 1255 858 2010 11 25
end
reflexivemsg 128264 asynchronous
  to durationcanvas_ref 128136
  yz 65 2015 msg operation_ref 129486 // "on_clicked_toolbar_select() : void"
  show_full_operations_definition default drawing_language default
  label_xy 80 47
msg 129928 asynchronous
  from durationcanvas_ref 128136
  to durationcanvas_ref 129800
  yz 105 2015 msg operation_ref 171528 // "present() : void"
  show_full_operations_definition default drawing_language default
  label_xy 157 93
reflexivemsg 130696 asynchronous
  to durationcanvas_ref 130568
  yz 251 2015 msg operation_ref 160776 // "on_clicked_button_accept() : void"
  show_full_operations_definition default drawing_language default
  label_xy 251 232
reflexivemsg 130952 synchronous
  to durationcanvas_ref 130824
  yz 1025 2025 msg operation_ref 170888 // "hide() : void"
  show_full_operations_definition default drawing_language default
  label_xy 247 1013
reflexivemsg 131976 asynchronous
  to durationcanvas_ref 131848
  yz 169 2015 msg operation_ref 159368 // "on_item_activated(in path : Path) : void"
  show_full_operations_definition default drawing_language default
  label_xy 399 157
msg 134024 synchronous
  from durationcanvas_ref 130568
  to durationcanvas_ref 133896
  yz 291 3005 msg operation_ref 176904 // "action_host_selected() : void"
  show_full_operations_definition default drawing_language default
  label_xy 254 283
msg 135432 synchronous
  from durationcanvas_ref 133896
  to durationcanvas_ref 135304
  yz 340 2015 msg operation_ref 173448 // "get_selected_items() : ArrayHandle_TreePaths"
  show_full_operations_definition default drawing_language default
  label_xy 473 328
msg 135560 return
  from durationcanvas_ref 135304
  to durationcanvas_ref 133896
  yz 360 2015 explicitmsg "item"
  show_full_operations_definition default drawing_language default
  label_xy 509 348
msg 135816 synchronous
  from durationcanvas_ref 133896
  to durationcanvas_ref 135688
  yz 408 2015 msg operation_ref 178568 // "create_host(in hostname : ustring, in ip : ustring, in description : ustring) : bool"
  show_full_operations_definition default drawing_language default
  args "item.col_hostname,
item.col_ip,
item.col_description"
  label_xy 627 400
reflexivemsg 136072 synchronous
  to durationcanvas_ref 135944
  yz 433 2025 explicitmsg "hosts.find()"
  show_full_operations_definition default drawing_language default
  args "hostname"
  label_xy 835 420
msg 136584 synchronous
  from durationcanvas_ref 135688
  to durationcanvas_ref 136456
  yz 601 2015 msg operation_ref 128067 // "Host()"
  show_full_operations_definition default drawing_language default
  label_xy 853 589
msg 137224 synchronous
  from durationcanvas_ref 135688
  to durationcanvas_ref 137096
  yz 642 2015 msg operation_ref 179720 // "set__hostname(in value : ustring) : void"
  show_full_operations_definition default drawing_language default
  label_xy 824 630
msg 137480 synchronous
  from durationcanvas_ref 135688
  to durationcanvas_ref 137352
  yz 677 2015 msg operation_ref 179848 // "set__ip(in value : ustring) : void"
  show_full_operations_definition default drawing_language default
  label_xy 832 665
msg 137736 synchronous
  from durationcanvas_ref 135688
  to durationcanvas_ref 137608
  yz 716 2015 msg operation_ref 179976 // "set__description(in value : ustring) : void"
  show_full_operations_definition default drawing_language default
  label_xy 821 704
msg 145032 return
  from durationcanvas_ref 135688
  to durationcanvas_ref 133896
  yz 985 2020 explicitmsg "created"
  show_full_operations_definition default drawing_language default
  label_xy 690 973
reflexivemsg 151432 synchronous
  to durationcanvas_ref 151304
  yz 770 2030 msg operation_ref 175624 // "notify() : void"
  show_full_operations_definition default drawing_language default
  label_xy 815 758
msg 152200 synchronous
  from durationcanvas_ref 151304
  to durationcanvas_ref 152072
  yz 786 2035 msg operation_ref 193416 // "update(inout s : Subject) : void"
  show_full_operations_definition default drawing_language default
  args "Host"
  label_xy 954 771
reflexivemsg 152456 synchronous
  to durationcanvas_ref 152328
  yz 798 2025 msg operation_ref 193288 // "add_host_page(inout host : Host) : void"
  show_full_operations_definition default drawing_language default
  args "Host"
  label_xy 1104 785
reflexivemsg 153224 synchronous
  to durationcanvas_ref 153096
  yz 916 2035 msg operation_ref 191752 // "append_page(inout child : Widget, in tab_label : ustring, in use_mnemonic : bool = false) : int"
  show_full_operations_definition default drawing_language default
  args "*tmp, Host.get__hostname"
  label_xy 1107 903
reflexivemsg 153480 synchronous
  to durationcanvas_ref 153352
  yz 945 2035 msg operation_ref 169224 // "show_all_children(in recursive : bool = true) : void"
  show_full_operations_definition default drawing_language default
  label_xy 1112 933
msg 153736 synchronous
  from durationcanvas_ref 152328
  to durationcanvas_ref 153608
  yz 821 2025 unspecifiedmsg
  show_full_operations_definition default drawing_language default
msg 153992 synchronous
  from durationcanvas_ref 152328
  to durationcanvas_ref 153864
  yz 858 3005 unspecifiedmsg
  show_full_operations_definition default drawing_language default
line 138248 -_-_
  from ref 136712 z 2019 to ref 138120
line 145928 -_-_
  from ref 145800 z 1999 to ref 141576
line 154120 -_-_
  from ref 153736 z 2019 to point 1245 797
  line 154504 z 2019 to ref 140552
line 154248 -_-_
  from ref 153992 z 1999 to point 1242 845
  line 154376 z 1999 to ref 141320
line 154632 -_-_
  from ref 129032 z 1999 to ref 133256
end
