format 56

artifactcanvas 128069 artifact_ref 129733 // utils
  xyz 581 190 2000
artifactcanvas 128105 artifact_ref 128069 // inode
  xyz 122 476 2005
artifactcanvas 128195 artifact_ref 128195 // host
  xyz 76 341 2000
artifactcanvas 128233 artifact_ref 128197 // hal-manager-proxy
  xyz 603 457 2000
artifactcanvas 128323 artifact_ref 128323 // process
  xyz 91 415 2000
artifactcanvas 128361 artifact_ref 128325 // hal-device-proxy
  xyz 607 358 2000
artifactcanvas 128489 artifact_ref 129897 // hal-controler
  xyz 531 521 2004
artifactcanvas 128579 artifact_ref 128451 // main
  color green
  xyz 289 197 2000
artifactcanvas 128604 artifact_ref 128604 // glkm
  color mediumyellow
  xyz 303 52 2000
artifactcanvas 128617 artifact_ref 130025 // log
  xyz 572 259 2009
artifactcanvas 129219 artifact_ref 128579 // file
  xyz 210 529 2000
artifactcanvas 129347 artifact_ref 128707 // filesystem
  xyz 340 554 2000
simplerelationcanvas 128092 simplerelation_ref 128092
  from ref 128579 z 1999 to ref 128195
simplerelationcanvas 128197 simplerelation_ref 128069
  from ref 128579 z 1999 to ref 128069
simplerelationcanvas 128220 simplerelation_ref 128220
  from ref 128579 z 1999 to ref 128323
simplerelationcanvas 128348 simplerelation_ref 128348
  from ref 128579 z 1999 to ref 129219
simplerelationcanvas 128476 simplerelation_ref 128476
  from ref 128579 z 1999 to ref 129347
containcanvas 128732
  from ref 128604 z 1999 to ref 128579
simplerelationcanvas 128745 simplerelation_ref 129897
  from ref 128579 z 1999 to ref 128617
simplerelationcanvas 128873 simplerelation_ref 130025
  from ref 128579 z 1999 to ref 128361
simplerelationcanvas 129001 simplerelation_ref 130153
  from ref 128579 z 1999 to ref 128233
simplerelationcanvas 129129 simplerelation_ref 130281
  from ref 128579 z 1999 to ref 128489
end
