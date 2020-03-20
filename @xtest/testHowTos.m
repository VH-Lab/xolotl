function failing = testHowTos(self)

    % strip code from all how-to's
    % run that code
    % make sure that there are no errors

    %% Get a list of all how-to's to test

    xolotl_path = pathlib.strip(mfilename('fullpath'), 2);
    how_tos_dir = fullfile(xolotl_path, 'docs', 'how-to');
    how_tos     = dir(how_tos_dir);

    %% Test all how-to's

    isFailing = false(length(how_tos), 1);
    test_filepath = fullfile(xolotl_path, 'test_how_tos.m');

    for ii = 3:length(how_tos)

        % strip the code
        filepath = fullfile(how_tos(ii).folder, how_tos(ii).name);
        stripped_code = stripCode(filepath);

        % save code in a temporary file
        filelib.write(test_filepath, stripped_code);

        % run the script and see if it works
        try
            test_how_tos;
            close all;
        catch
            isFailing(ii) = true;
        end

    end

    %% Output & cleanup

    failing = how_tos(isFailing);
    delete(test_filepath);

end % function

function stripped_code = stripCode(filepath)
    % slurp the file into a cell array of character vectors
    % line by line
    this_file = filelib.read(filepath);

    % define start and stop blocks
    start = '```matlab';
    stop = '```';

    % acquire linear indices of start and stop times
    starts = find(strcmp(this_file, start));
    stops = find(strcmp(this_file, stop));

    % determine which lines to keep
    keep_these = false(length(this_file), 1);
    for ii = 1:length(starts)
        keep_these(starts(ii)+1:stops(ii)-1, 1) = true;
    end

    stripped_code = this_file(keep_these);

end % function
