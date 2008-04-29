format 55

artifactcanvas 128195 artifact_ref 128195 // host
  xyz 76 341 2000
artifactcanvas 128323 artifact_ref 128323 // process
  xyz 177 450 2000
artifactcanvas 128579 artifact_ref 128451 // main
  color green
  xyz 314 198 2000
artifactcanvas 128604 artifact_ref 128604 // glkm
  color mediumyellow
  xyz 303 52 2000
artifactcanvas 129219 artifact_ref 128579 // file
  xyz 452 453 2000
artifactcanvas 129347 artifact_ref 128707 // filesystem
  xyz 535 350 2000
simplerelationcanvas 128092 simplerelation_ref 128092
  from ref 128579 z 1999 to ref 128195
simplerelationcanvas 128220 simplerelation_ref 128220
  from ref 128579 z 1999 to ref 128323
simplerelationcanvas 128348 simplerelation_ref 128348
  from ref 128579 z 1999 to ref 129219
simplerelationcanvas 128476 simplerelation_ref 128476
  from ref 128579 z 1999 to ref 129347
containcanvas 128732
  from ref 128604 z 1999 to ref 128579
end
