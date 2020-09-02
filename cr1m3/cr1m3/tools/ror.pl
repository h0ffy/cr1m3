#!/usr/bin/perl -w
use strict;
sub ror {
my $number = shift;
my $bitshift = shift;
return ($number >> $bitshift) | ($number << (32 - $bitshift));
}
sub hash {
my @name = unpack("C*",shift);
my $hash = 0;
for(my $i=0; $i<=$#name; $i++) {
$hash = ror($hash, 0x4A) + $name[$i];
}
return $hash;
}
while(<>) {
chomp;
printf ("%08x\t%s\n", hash($_),$_); #modify this line if you want SQL or HTML, &c.
printf ("%.8x\t%s\n", hash($_),$_); #modify this line if you want SQL or HTML, &c.
}
