function varargout = GUI(varargin)
% GUI MATLAB code for GUI.fig
%      GUI, by itself, creates a new GUI or raises the existing
%      singleton*.
%
%      H = GUI returns the handle to a new GUI or the handle to
%      the existing singleton*.
%
%      GUI('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in GUI.M with the given input arguments.
%
%      GUI('Property','Value',...) creates a new GUI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before GUI_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to GUI_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help GUI

% Last Modified by GUIDE v2.5 08-Jun-2017 16:35:08

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @GUI_OpeningFcn, ...
                   'gui_OutputFcn',  @GUI_OutputFcn, ...
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


% --- Executes just before GUI is made visible.
function GUI_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to GUI (see VARARGIN)

% Choose default command line output for GUI
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes GUI wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = GUI_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in btnDiagnose.
function btnDiagnose_Callback(hObject, eventdata, handles)
rbc = str2double(get(handles.txtRBC, 'String'));
hb = str2double(get(handles.txtHb, 'String'));
ht = str2double(get(handles.txtHt, 'String'));
mcv = str2double(get(handles.txtMCV, 'String'));
hba2 = str2double(get(handles.txtHbA2, 'String'));

isBeta = false;
isNormal = false;
isAlpha = false;

X(1,:) = rbc;
X(2,:) = hb;
X(3,:) = ht;
X(4,:) = mcv;
X(5,:) = hba2;

save('diagnose.mat', 'X');
run('diagnosis\betaVS(norm,alpha)2c5f\rbf.m');
fid = fopen('diagnosis\betaVS(norm,alpha)2c5f\rbf_output.dat', 'rt');
betaOutput = textscan(fid, '%f %f %f');
betaResult = betaOutput{2};
rbfOutput = betaOutput{1};
threshold = betaOutput{3};
fclose(fid);
if betaResult == 2
    isBeta = true;
else
    run('diagnosis\normVSalpha\rbf.m');
    fid = fopen('diagnosis\normVSalpha\rbf_output.dat', 'rt');
    alphaNormOutput = textscan(fid, '%f %f %f');
    alphaNormResult = alphaNormOutput{2};
    rbfOutput = alphaNormOutput{1};
    threshold = alphaNormOutput{3};
    fclose(fid);
    if alphaNormResult == 1
        isNormal = true;
    else
        isAlpha = true;
    end
end

if isNormal == true
    set(handles.txtDiagnosis, 'String', 'Normal patient');
elseif isBeta == true
    set(handles.txtDiagnosis, 'String', 'beta-thalassaemia carrier');
else 
    set(handles.txtDiagnosis, 'String', 'alpha-thalassaemia carrier');
end
set(handles.txtRBF, 'String', rbfOutput);
set(handles.txtThreshold, 'String', threshold);

% --- Executes on button press in btnSave.
function btnSave_Callback(hObject, eventdata, handles)
% hObject    handle to btnSave (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in btnDatabase.
function btnDatabase_Callback(hObject, eventdata, handles)
% hObject    handle to btnDatabase (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)



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


function txtRBF_Callback(hObject, eventdata, handles)
% hObject    handle to txtRBF (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of txtRBF as text
%        str2double(get(hObject,'String')) returns contents of txtRBF as a double


% --- Executes during object creation, after setting all properties.
function txtRBF_CreateFcn(hObject, eventdata, handles)
% hObject    handle to txtRBF (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function txtThreshold_Callback(hObject, eventdata, handles)
% hObject    handle to txtThreshold (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of txtThreshold as text
%        str2double(get(hObject,'String')) returns contents of txtThreshold as a double


% --- Executes during object creation, after setting all properties.
function txtThreshold_CreateFcn(hObject, eventdata, handles)
% hObject    handle to txtThreshold (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
