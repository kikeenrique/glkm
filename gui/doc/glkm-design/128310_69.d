format 56

usecasecanvas 128029 usecase_ref 128029 // mostrar procesos
  xyzwh 614 145 3005 64 32 label_xy 606 177
classcanvas 128054 class_ref 128182 // developer
  class_drawing_mode default show_context_mode default
  xyz 81 122 3015
usecasecanvas 128121 usecase_ref 128121 // seleccionar m�quina
  xyzwh 619 64 3005 64 32 label_xy 606 96
usecasecanvas 128249 usecase_ref 128249 // seleccionar procesos
  xyzwh 620 233 3005 64 32 label_xy 605 265
usecasecanvas 128310 usecase_ref 128310 // monitorizar procesos
  xyzwh 340 136 3005 64 32 label_xy 319 167
usecasecanvas 128413 usecase_ref 128157 // mostrar informaci�n procesos
  xyzwh 499 339 3005 64 32 label_xy 462 371
simplerelationcanvas 128285 simplerelation_ref 128029
  from ref 128310 z 3004 stereotype "<<include>>" xyz 480 153 3000 to ref 128029
simplerelationcanvas 128505 simplerelation_ref 128121
  from ref 128121 z 3004 stereotype "<<extend>>" xyz 481 113 3000 to ref 128310
line 129913 ----
  from ref 128054 z 3004 to ref 128310
simplerelationcanvas 130041 simplerelation_ref 128249
  from ref 128249 z 3004 stereotype "<<extend>>" xyz 482 198 3000 to ref 128310
end
