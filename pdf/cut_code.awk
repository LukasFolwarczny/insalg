#!/bin/awk -f
BEGIN { do_print = false }
/\/\*pdf\*\// { do_print = !do_print; getline }
{ if (do_print) print }
