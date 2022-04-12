#!/usr/bin/perl -w
print "Content-type: text/html\n\n";
foreach $key (sort keys(%ENV)) {
  print "$key = $ENV{$key}<p>";
}
print "</pre>\n";