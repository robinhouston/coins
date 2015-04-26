#!/usr/bin/perl

my %p = (
        "1" => 0,
        "2" => 1,
        "5" => 2,
        "10" => 3,
        "20" => 4,
        "50" => 5,
        "100" => 6,
        "200" => 7,
);

print "<table>\n";

open(my $f, "<", "coins-results.txt") or die "Failed to open coins-results.txt: $!\n";
my @ent = ("") x 8;
while (<$f>) {
        if (/^(\d+) x (\d+)p coins$/) {
                $ent[$p{$2}] = $1;
        }
        elsif (/^$/) {
                print "<tr>" . join("", map "<td>$_</td>", @ent) . "</tr>\n";
                @ent = ("") x 8;
        }
        else {
                die "Unrecognised line in file: $_\n";
        }
}

print "</table>\n";
