format 56

artifactcanvas 128078 artifact_ref 129733 // utils
  xyz 594 306 2004
artifactcanvas 128092 artifact_ref 128476 // aboutdialog
  xyz 136 396 2000
artifactcanvas 128220 artifact_ref 128092 // mainwindow
  xyz 286 290 2000
artifactcanvas 128348 artifact_ref 128220 // statusbar
  xyz 437 395 2000
artifactcanvas 128476 artifact_ref 128348 // treeviewhost
  xyz 286 442 2000
artifactcanvas 129116 artifact_ref 128604 // glkm
  color mediumyellow
  xyz 274 27 2000
artifactcanvas 129244 artifact_ref 128451 // main
  xyz 286 165 2004
simplerelationcanvas 128206 simplerelation_ref 128069
  from ref 129244 z 1999 to ref 128078
simplerelationcanvas 128604 simplerelation_ref 128604
  from ref 128220 z 1999 to ref 128092
simplerelationcanvas 128732 simplerelation_ref 128732
  from ref 128220 z 1999 to ref 128476
simplerelationcanvas 128860 simplerelation_ref 128860
  from ref 128220 z 1999 to ref 128348
containcanvas 129372
  from ref 129116 z 1999 to ref 129244
simplerelationcanvas 129500 simplerelation_ref 128988
  from ref 129244 z 1999 to ref 128220
end
