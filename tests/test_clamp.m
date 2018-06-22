
vol = 0.0628; % this can be anything, doesn't matter
f = 1.496; % uM/nA
tau_Ca = 200;
F = 96485; % Faraday constant in SI units
phi = (2*f*F*vol)/tau_Ca;
Ca_target = 0; % used only when we add in homeostatic control 

x = xolotl;
x.add('compartment','AB','Cm',10,'A',0.0628,'vol',vol,'phi',phi,'Ca_out',3000,'Ca_in',0.05,'tau_Ca',tau_Ca,'Ca_target',Ca_target);

x.AB.add('liu-approx/NaV','gbar',@() 115/x.AB.A,'E',30);
x.AB.add('liu-approx/CaT','gbar',@() 1.44/x.AB.A,'E',30);
x.AB.add('liu-approx/Kd','gbar',@() 38.31/x.AB.A,'E',-80);
x.AB.add('Leak','gbar',@() 0.0622/x.AB.A,'E',-50);

holding_V = -60;
all_V_step = linspace(-80,50,30);

x.t_end = 5e2;
x.sim_dt = .1;
x.dt = .1;

all_I = NaN(x.t_end/x.dt,length(all_V_step));
all_V_step = repmat(all_V_step,x.t_end/x.dt,1);

x.V_clamp = repmat(holding_V,x.t_end/x.dt,1);


x.integrate;
x.closed_loop = false;

for i = 1:size(all_V_step,2)
	x.V_clamp = all_V_step(:,i);
	all_I(:,i) = x.integrate;
end

time = (1:length(all_I))*x.dt;

figure('outerposition',[300 300 1200 600],'PaperUnits','points','PaperSize',[1200 600]); hold on
subplot(1,2,1); hold on
c = parula(size(all_V_step,2));
for i = 1:size(all_V_step,2)
	plot(time,all_I(:,i),'Color',c(i,:))
end
xlabel('Time (ms)')
ylabel('Current (nA)')
set(gca,'XScale','log')

subplot(1,2,2); hold on
plot(all_V_step,all_I(end,:),'r')
xlabel('Voltage step (mV)')
ylabel('Current (nA)')

prettyFig();
drawnow
