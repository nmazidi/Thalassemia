function varargout = dataGUI(varargin)
% DATAGUI MATLAB code for dataGUI.fig
%      DATAGUI, by itself, creates a new DATAGUI or raises the existing
%      singleton*.
%
%      H = DATAGUI returns the handle to a new DATAGUI or the handle to
%      the existing singleton*.
%
%      DATAGUI('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in DATAGUI.M with the given input arguments.
%
%      DATAGUI('Property','Value',...) creates a new DATAGUI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before dataGUI_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to dataGUI_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help dataGUI

% Last Modified by GUIDE v2.5 13-Jun-2017 12:11:55

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @dataGUI_OpeningFcn, ...
                   'gui_OutputFcn',  @dataGUI_OutputFcn, ...
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


% --- Executes just before dataGUI is made visible.
function dataGUI_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to dataGUI (see VARARGIN)

% Choose default command line output for dataGUI
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes dataGUI wait for user response (see UIRESUME)
% uiwait(handles.figure1);
data = xlsread('records.xlsx');
set(handles.tblData, 'columnname',{'ID','RBC','Hb','Ht','MCV','HbA2','Diagnosis'});
set(handles.tblData, 'Data',data);


% --- Outputs from this function are returned to the command line.
function varargout = dataGUI_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;
