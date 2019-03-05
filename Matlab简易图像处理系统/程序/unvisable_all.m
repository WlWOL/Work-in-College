function unvisable_all(handles)
cla(handles.axes1,'reset'); 
cla(handles.axes2,'reset');
cla(handles.axes3,'reset'); 
cla(handles.axes4,'reset');
cla(handles.axes5,'reset'); 
cla(handles.axes6,'reset');

set(handles.axes1,'visible','off');
set(handles.axes2,'visible','off');
set(handles.axes3,'visible','off');
set(handles.axes4,'visible','off');
set(handles.axes5,'visible','off');
set(handles.axes6,'visible','off');


set(handles.slider1,'visible','off');
set(handles.text1,'visible','off');
set(handles.slider2,'visible','off');
set(handles.text2,'visible','off');
set(handles.slider3,'visible','off');
set(handles.text3,'visible','off');
end