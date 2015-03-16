# Analysis Report #

This page details the contents of the analysis report.

# Purpose #

The framework offers the generation of a report including details of the implementation
and some analysis information.

# Contents #

  * environment details: LSB information, hardware and others
  * line-of-code stats: sloccount output
  * execution sample: verbose execution output
  * gprof output: execution profile information
  * valgrind output: memory debugging information
  * process scaling: timings when process number is increased
  * resource usage: %CPU, %MEM
  * MPI profiling

# Generation #

The PDF report is generated using LaTeX and gnuplot.

# Details #

## Environment ##

The output of the following commands are used to extract hardware information.

cat /proc/cpuinfo | grep 'model name' | uniq
cat /proc/meminfo

The output of the following commands are used to extract software information.

uname -a
lsb\_release -a

## Source Code ##

The output of sloccount is used to dimension the source code.

## Execution Output ##

The console output of a sample execution is pasted here

## Execution Log ##

The full execution log is shown here.

## Profiling Information ##

The output of gprof is pasted here.
The output of valgrind is pasted here.

## Scaling Information ##

According to each system, scaled executions are reported here.
execution time is used as indicator.

## Resource Usage Charts ##

The %CPU, %MEM values from top are used to build a graph using gnuplot to provide insights of the resource usage of the systems during the execution of the application.