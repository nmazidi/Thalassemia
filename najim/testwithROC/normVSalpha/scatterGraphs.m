subplot(3,2,1);
scatter(X(:,2),X(:,1),'filled');
title('Classes distribution');
xlabel('Hb A1 (g/ dL)');
ylabel('RBC (x 10^12/L)');

subplot(3,2,2);
scatter(X(:,3),X(:,1),'filled');
title('Classes distribution');
xlabel('Ht (%)');
ylabel('RBC (x 10^12/L)');

subplot(3,2,3);
scatter(X(:,4),X(:,1),'filled');
title('Classes distribution');
xlabel('MCV (fL)');
ylabel('RBC (x 10^12/L)');

subplot(3,2,4);
scatter(X(:,5),X(:,1),'filled');
title('Classes distribution');
xlabel('Hb A2 (g/ dL)');
ylabel('RBC (x 10^12/L)');

subplot(3,2,5);
scatter(X(:,3),X(:,2),'filled');
title('Classes distribution');
xlabel('Ht (%)');
ylabel('Hb A1 (g/ dL)');