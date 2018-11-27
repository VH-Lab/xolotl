

function [passed, total] = run_all_tests(cleanup)

if nargin < 1
	cleanup = false;
end

if cleanup
	xolotl.cleanup;
end

% rebuild cpplab cache just to be safe
cpplab.rebuildCache;

% compile GetMD5
ok = InstallMex('GetMD5.c');

this_dir = fileparts(fileparts(which(mfilename)));
all_tests = dir(joinPath(this_dir,'examples','demo*.m'));	

cd(joinPath(this_dir,'examples'))
	

passed = 0;
total = length(all_tests);


for i = length(all_tests):-1:1	
	disp(['Running test: ' all_tests(i).name])	
	try	
		[~,script_name] = fileparts(all_tests(i).name);
		evalin('base',script_name);
		pause(1)	
		close all	
		% clearvars -except all_tests i 	
		disp('TEST PASSED')	
		passed = passed + 1;
	catch err
		disp('TEST FAILED')	
	end	
end 