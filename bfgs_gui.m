%姓名：林汶尭 学号：6320000607 邮箱：wenn_yaw@hotmail.com 
function bfgs_gui()
    % Create the main figure
    fig = figure('Position', [100, 100, 800, 600], 'Name', 'BFGS Optimization GUI', 'NumberTitle', 'off', 'MenuBar', 'none', 'ToolBar', 'none', 'CloseRequestFcn', @closeApp);

    % UI controls for input parameters
    uicontrol('Style', 'text', 'Position', [20, 540, 400, 30], 'String', 'Enter Objective Function:', 'FontSize', 10, 'HorizontalAlignment', 'left');
    input_objective_function = uicontrol('Style', 'edit', 'Position', [20, 500, 280, 30]);

    uicontrol('Style', 'text', 'Position', [20, 450, 120, 30], 'String', 'Initial Point (x1, x2):');
    input_x1 = uicontrol('Style', 'edit', 'Position', [150, 450, 50, 30]);
    input_x2 = uicontrol('Style', 'edit', 'Position', [210, 450, 50, 30]);
    
    uicontrol('Style', 'text', 'Position', [20, 400, 120, 30], 'String', 'Epsilon:');
    input_epsilon = uicontrol('Style', 'edit', 'Position', [150, 400, 100, 30]);
    
    uicontrol('Style', 'text', 'Position', [20, 350, 120, 30], 'String', 'Max Iterations:');
    input_max_iter = uicontrol('Style', 'edit', 'Position', [150, 350, 100, 30]);
    
    % Button to trigger the optimization
    optimize_button = uicontrol('Style', 'pushbutton', 'Position', [20, 300, 100, 30], 'String', 'Optimize', 'Callback', @runOptimization);
    
    % Plot area for optimization path
    plot_axes = axes('Parent', fig, 'Position', [0.5, 0.1, 0.45, 0.8]);

    % Text box to display iteration results
    iteration_textbox = uicontrol('Style', 'edit', 'Position', [20, 150, 300, 130], 'Max', 10, 'HorizontalAlignment', 'left', 'Enable', 'inactive');

    % Text box to display final result
    result_textbox = uicontrol('Style', 'text', 'Position', [20, 20, 300, 100], 'HorizontalAlignment', 'left', 'String', '');

    function runOptimization(~, ~)
        try
            % Get user input
            objective_function_str = get(input_objective_function, 'String');
            initial_x1 = str2double(get(input_x1, 'String'));
            initial_x2 = str2double(get(input_x2, 'String'));
            epsilon = str2double(get(input_epsilon, 'String'));
            max_iterations = str2double(get(input_max_iter, 'String'));
            
            % Check if any of the input is empty or not a number
            if any(isnan([initial_x1, initial_x2, epsilon, max_iterations]))
                error('All inputs must be numeric.');
            end
            
            % Run BFGS algorithm with the user-defined objective function
            objective_function = str2func(['@(x1, x2) ', objective_function_str]);
            [X, opt_values, iteration_results] = BFGS(objective_function, [initial_x1; initial_x2], epsilon, max_iterations);
            
            % Plot the function and the optimization path
            plot(plot_axes, X(:, 1), X(:, 2), 'ro-');
            hold(plot_axes, 'on');
            ezcontour(plot_axes, objective_function, [-10, 10], 100);
            xlabel(plot_axes, 'x1');
            ylabel(plot_axes, 'x2');
            title(plot_axes, 'Optimization Path');
            hold(plot_axes, 'off');
            
            % Display optimization results
            disp('Optimization results:');
            disp('Optimal point:');
            disp(X(end, :));
            disp('Optimal function value:');
            disp(opt_values(end));
            
            % Display iteration results
            set(iteration_textbox, 'String', iteration_results);
            
            % Display final result
            set(result_textbox, 'String', sprintf('Result:\nOptimal Point: [%s]\nOptimal Function Value: %s', num2str(X(end, :)), num2str(opt_values(end))));
        catch exception
            % Display error message if an error occurs
            errordlg(['An error occurred: ' exception.message], 'Error', 'modal');
        end
    end

    function closeApp(~, ~)
        delete(fig);
    end
end 

function [X, opt_values, iteration_results] = BFGS(f, x0, eps, k)
% BFGS algorithm implementation
    x0 = x0(:);  % Ensure x0 is a column vector
    TiDu = matlabFunction(gradient(sym(f)));
    m = length(x0);
    A = eye(m);  % Initial matrix

    f_cal = sprintf('f(%f,%f)', x0(1), x0(2));
    tidu_cal = 'TiDu(x0(1),x0(2))';
    f1_cal = 'f(x_1(1),x_1(2))';

    f_x0 = eval(f_cal);
    tidu_x0 = eval(tidu_cal);
    if norm(tidu_x0) < eps
        X = x0';
        opt_values = f_x0;
        iteration_results = '';
        return;
    end

    d = -A * tidu_x0;  % Descent direction

    X = x0';
    opt_values = f_x0;

    iteration_results = '';

    n = 1;
    while n <= k && norm(tidu_x0) > eps
        syms alfa
        x_1 = x0 + alfa * d;
        f_x1 = eval(f1_cal);
        df_x1 = diff(f_x1);
        dalfa = double(solve(df_x1));
        x0 = x0 + dalfa .* d;  % Use element-wise addition
        tidu_x1 = eval(tidu_cal);

        delta_x = dalfa .* d;  % Use element-wise multiplication
        delta_g = tidu_x1 - tidu_x0;  % Use element-wise subtraction
        delta_A = (delta_x * delta_x') / (delta_x' * delta_g) - (A * delta_g * delta_g' * A') / (delta_g' * A * delta_g);
        A = A + delta_A;
        tidu_x0 = tidu_x1;

        d = -A * tidu_x0;  % Descent direction

        % Append current iteration information to the results
        iteration_results = [iteration_results, sprintf('Iteration: %d\n', n)];
        iteration_results = [iteration_results, sprintf('Current point: [%s]\n', num2str(x0'))];
        iteration_results = [iteration_results, sprintf('Current gradient: [%s]\n', num2str(tidu_x1'))];
        iteration_results = [iteration_results, sprintf('Descent direction: [%s]\n', num2str(d'))];
        iteration_results = [iteration_results, sprintf('Step length: %s\n', num2str(dalfa))];
        iteration_results = [iteration_results, sprintf('Current function value: %s\n', num2str(eval(f_cal)))];
        iteration_results = [iteration_results, '----------------------------------', newline];

        % Append current point and function value to the results
        X = [X; x0'];
        opt_values = [opt_values; eval(f_cal)];

        n = n + 1;
    end
end
