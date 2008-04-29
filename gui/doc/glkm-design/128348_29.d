format 55

deploymentnodecanvas 128476 deploymentnode_ref 128092 // host_A
  xyzwh 223 263 2000 58 44
deploymentnodecanvas 128604 deploymentnode_ref 128220 // monitor
  xyzwh 337 101 2000 58 44
hubcanvas 128860 xyz 248 210 2005
hubcanvas 129500 xyz 474 210 2005
hubcanvas 130396 xyz 363 210 2009
deploymentnodecanvas 131036 deploymentnode_ref 128348 // host_N
  xyzwh 448 264 2005 58 44
hubcanvas 131292 xyz 591 211 2000
line 130012 ----
  from ref 128860 z 1999 to ref 128476
line 130652 ----
  from ref 128860 z 2004 to ref 130396
line 130780 ----
  from ref 130396 z 2004 to ref 129500
line 130908 ----
  from ref 130396 z 1999 to ref 128604
line 131164 ----
  from ref 131036 z 2004 to ref 129500
line 131420 ----
  from ref 129500 z 1999 label "network" xyz 515 200 1999 to ref 131292
end
