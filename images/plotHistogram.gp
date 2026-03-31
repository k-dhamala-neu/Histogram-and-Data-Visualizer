set terminal png
set output 'images/histogram.png'
set title 'Histogram'
set xlabel 'Value'
set ylabel 'Frequency'
set datafile separator ','
set boxwidth 1.4 absolute
set style fill solid border -1
unset autoscale
set yrange [0:8] noreverse
set xrange [0.1:9.9]
set xtics ('1.5-2.9' 2.2, '2.9-4.3' 3.6, '4.3-5.7' 5, '5.7-7.1' 6.4, '7.1-8.5' 7.8)
plot 'images/histogram.csv' skip 1 using (($1+$2)/2):3 with boxes notitle
