#!/usr/bin/perl

use strict;

sub usage() {
    print STDERR "Usage: $0 <dep file> ...\n";
    exit(1);
}

# main
my $depfile;

#print STDERR "CHECK_DEPS: @ARGV\n";

for $depfile (@ARGV) {
#    print STDERR "DEP: $depfile\n";
    my (@rule, $file, $line);
    # Read entire dep file into an array
    open (IN, $depfile) or die("$0: Cannot open $depfile: $!\n");
    @rule = <IN>;
    close(IN);
    # Make the rule more manageable
    $line = join(" ",@rule);
    $line =~ s@\\\n@@gm;
    $line =~ s@\s+@ @g;
    $line =~ s@^\s*@@g;
    $line =~ s@\s+$@@g;
    my ($target, $deps) = split(/\s*:\s*/,$line, 2);
#    print STDERR "TARGET: $target\n";
    @rule = split(/\s+/, $deps);
    if ($target eq "") {
	print STDERR "Error: $0: Cannot determine target from\n\t$line\n";
	exit(1);
    }
    for $file (@rule) {
#	print STDERR "FILE: |$file|\n";
	if (! -e $file) {
#	    print STDERR "FORCE: |$file|\n";
	    open(OUT, ">$depfile") || die("$0: Cannot write to $depfile: $!\n");
	    print OUT "${target}: FORCE\n";
	    close(OUT);
	    last;
	}
    }
}
