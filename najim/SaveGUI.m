function varargout = SaveGUI(varargin)
% SAVEGUI MATLAB code for SaveGUI.fig
%      SAVEGUI, by itself, creates a new SAVEGUI or raises the existing
%      singleton*.
%
%      H = SAVEGUI returns the handle to a new SAVEGUI or the handle to
%      the existing singleton*.
%
%      SAVEGUI('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in SAVEGUI.M with the given input arguments.
%
%      SAVEGUI('Property','Value',...) creates a new SAVEGUI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before SaveGUI_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to SaveGUI_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help SaveGUI

% Last Modified by GUIDE v2.5 12-Jun-2017 15:41:56

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @SaveGUI_OpeningFcn, ...
                   'gui_OutputFcn',  @SaveGUI_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before SaveGUI is made visible.
function SaveGUI_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to SaveGUI (see VARARGIN)

% Choose default command line output for SaveGUI
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes SaveGUI wait for user response (see UIRESUME)
% uiwait(handles.figure1);

set(handles.txtRBC,'String',getappdata(0,'rbc'));
set(handles.txtHb,'String',getappdata(0,'hb'));
set(handles.txtHt,'String',getappdata(0,'ht'));
set(handles.txtMCV,'String',getappdata(0,'mcv'));
set(handles.txtHbA2,'String',getappdata(0,'hba2'));
set(handles.txtDiagnosis,'String',getappdata(0,'cad'));

% --- Outputs from this function are returned to the command line.
function varargout = SaveGUI_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;

% --- Executes on button press in btnSave.
function btnSave_Callback(hObject, eventdata, handles)
rbc = str2double(get(handles.txtRBC, 'String'));
hb = str2double(get(handles.txtHb, 'String'));
ht = str2double(get(handles.txtHt, 'String'));
mcv = str2double(get(handles.txtMCV, 'String'));
hba2 = str2double(get(handles.txtHbA2, 'String'));
cad = get(handles.txtDiagnosis, 'String');
patid = get(handles.txtDiagnosis, 'String');
diag = get(handles.txtChoose, 'String');


function txtRBC_Callback(hObject, eventdata, handles)
% hObject    handle to txtRBC (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of txtRBC as text
%        str2double(get(hObject,'String')) returns contents of txtRBC as a double


% --- Executes during object creation, after setting all properties.
function txtRBC_CreateFcn(hObject, eventdata, handles)
% hObject    handle to txtRBC (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function txtHb_Callback(hObject, eventdata, handles)
% hObject    handle to txtHb (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of txtHb as text
%        str2double(get(hObject,'String')) returns contents of txtHb as a double


% --- Executes during object creation, after setting all properties.
function txtHb_CreateFcn(hObject, eventdata, handles)
% hObject    handle to txtHb (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function txtHt_Callback(hObject, eventdata, handles)
% hObject    handle to txtHt (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of txtHt as text
%        str2double(get(hObject,'String')) returns contents of txtHt as a double


% --- Executes during object creation, after setting all properties.
function txtHt_CreateFcn(hObject, eventdata, handles)
% hObject    handle to txtHt (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function txtMCV_Callback(hObject, eventdata, handles)
% hObject    handle to txtMCV (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of txtMCV as text
%        str2double(get(hObject,'String')) returns contents of txtMCV as a double


% --- Executes during object creation, after setting all properties.
function txtMCV_CreateFcn(hObject, eventdata, handles)
% hObject    handle to txtMCV (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function txtHbA2_Callback(hObject, eventdata, handles)
% hObject    handle to txtHbA2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of txtHbA2 as text
%        str2double(get(hObject,'String')) returns contents of txtHbA2 as a double


% --- Executes during object creation, after setting all properties.
function txtHbA2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to txtHbA2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function txtDiagnosis_Callback(hObject, eventdata, handles)
% hObject    handle to txtDiagnosis (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of txtDiagnosis as text
%        str2double(get(hObject,'String')) returns contents of txtDiagnosis as a double


% --- Executes during object creation, after setting all properties.
function txtDiagnosis_CreateFcn(hObject, eventdata, handles)
% hObject    handle to txtDiagnosis (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function txtID_Callback(hObject, eventdata, handles)
% hObject    handle to txtID (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of txtID as text
%        str2double(get(hObject,'String')) returns contents of txtID as a double


% --- Executes during object creation, after setting all properties.
function txtID_CreateFcn(hObject, eventdata, handles)
% hObject    handle to txtID (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function txtChoose_Callback(hObject, eventdata, handles)
% hObject    handle to txtChoose (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of txtChoose as text
%        str2double(get(hObject,'String')) returns contents of txtChoose as a double


% --- Executes during object creation, after setting all properties.
function txtChoose_CreateFcn(hObject, eventdata, handles)
% hObject    handle to txtChoose (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
