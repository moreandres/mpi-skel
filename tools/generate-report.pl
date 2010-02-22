#! /usr/bin/perl

# $Id: $

package main;

use strict;
use warnings;
use English qw( -no_match_vars );

our $VERSION = 1.0;

sub execute {
    my ($command) = @ARG;

    use IPC::Open3 'open3';
    $SIG{'CHLD'} = 'IGNORE';

    my ( $writer, $reader, $err );
    my ( $stdout, $stderr );

    if ( defined $command ) {

        open3( $writer, $reader, $err, $command );

        my $line;

        while ( $line = <$reader> ) {
            $stdout .= $line;
        }

        while ( defined $err and $line = <$err> ) {
            $stderr .= $line;
        }
    }

    if (wantarray) {
        return ( $stdout, $stderr );
    }
    else {

        if ( defined $stderr ) {
            $stdout .= $stderr;
        }

        return $stdout;
    }
}

my ($distro) = execute('lsb_release --all');
my ($cpu)    = execute('cat /proc/cpuinfo');
my ($mem)    = execute('cat /proc/meminfo');

1;
