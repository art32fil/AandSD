function research()
  file = fopen('Research.txt', 'rt');
  N = fscanf(file, '%d', 1);
  M = fscanf(file, '%d', 1);
  for i = 1:N
    for j = 1:M
      A(i,j) = fscanf(file, '%g', 1);
    end;
  end;
  fclose(file);
  x = A(1:7700);
  y = A(7701:15400);
  x_t = 0:0.01:7700;
  y_t  = log2(x_t);
  h = figure();
  h = plot(x, y, "-b; depth(num of elements) - practice;");
  h2 = figure();
  h2 = plot(x_t, y_t, "-r; depth(num of elements) - theory;");
  saveas(h, "research.png");
  saveas(h2, "research2.png");

  endfunction;

  
  
  
  
  
