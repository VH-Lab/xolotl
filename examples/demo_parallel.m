% In this example, we demonstrate how
% xolotl can be run in parallel to quickly 
% scan a region in parameter space and 
% to analyze its behaviour there
% 
% Here, we will simulate 625 models in parallel
% and measure their burst metrics and plot them


clearvars

x = xolotl.examples.neurons.BurstingNeuron('prefix','liu');
x.dt = .1;
x.sim_dt = .1;
x.t_end = 10e3;

% try to download a binary
% so that people without compilers can use this too
try
	x.download
end


% The point of having this integrate call outside the parallel loop
% is to force a compilation. If you don't do this, you will get 
% and error
x.integrate;

% in this example, we are going to vary the maximal 
% conductances of the Acurrent and the slow calcium conductance in a grid
% using wildcards ('*') makes this code work for any model, 
% no matter what the compartment is
parameters_to_vary = {'*.CaS.gbar','*.ACurrent.gbar'};

g_CaS_space = linspace(0,100,25);
g_A_space = linspace(100,300,25);


[X, Y] = meshgrid(g_CaS_space, g_A_space);
all_params = [X(:), Y(:)]';



burst_period = NaN(length(all_params),1);
n_spikes_per_burst = NaN(length(all_params),1);

% run the simulations in parallel
tic
parfor i = 1:length(all_params)
	x.reset;

	x.set(parameters_to_vary,all_params(:,i));

	x.integrate;
	V = x.integrate; 


	metrics = xtools.V2metrics(V,'sampling_rate',1/x.dt,'ibi_thresh',100);

	burst_period(i) = metrics.burst_period;
	n_spikes_per_burst(i) = metrics.n_spikes_per_burst_mean;


end
t = toc;




disp(['Finished in ' mat2str(t,3) ' seconds. Total speed = ' mat2str(2*(length(all_params)*x.t_end*1e-3)/t,4) 'X'])


% assemble the data into a matrix for display
BP_matrix = NaN(length(g_CaS_space),length(g_A_space));
NS_matrix = NaN(length(g_CaS_space),length(g_A_space));
for i = 1:length(all_params)
	xx = find(all_params(1,i) == g_CaS_space);
	y = find(all_params(2,i) == g_A_space);
	BP_matrix(xx,y) = burst_period(i);
	NS_matrix(xx,y) = n_spikes_per_burst(i);
end
BP_matrix(BP_matrix<0) = NaN;
NS_matrix(NS_matrix<0) = 0;

figure('outerposition',[0 0 1200 600],'PaperUnits','points','PaperSize',[1200 600]); hold on

subplot(1,2,1)
imagesc(BP_matrix,'AlphaData',~isnan(BP_matrix));
[L,loc] = axlib.makeTickLabels(g_CaS_space,6);
set(gca,'YTick',loc,'YTickLabels',L)
[L,loc] = axlib.makeTickLabels(g_A_space,6);
set(gca,'XTick',loc,'XTickLabels',L)
ylabel('g_{CaS}')
xlabel('g_A')
title('Burst period (ms)')
axis xy
axis square
colorbar

subplot(1,2,2)
imagesc(NS_matrix,'AlphaData',~isnan(NS_matrix));
[L,loc] = axlib.makeTickLabels(g_CaS_space,6);
set(gca,'YTick',loc,'YTickLabels',L)
[L,loc] = axlib.makeTickLabels(g_A_space,6);
set(gca,'XTick',loc,'XTickLabels',L)
ylabel('g_{CaS}')
xlabel('g_A')
title('#spikes/burst')
axis xy
axis square
colorbar

figlib.pretty();


clearvars