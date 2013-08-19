#!/bin/awk -f
BEGIN { system("cat header.tex")
	FS = ":" }
$1 == "section" {
	print "\\section*{" $2 "}\n"
}
$1 == "subsection" {
	print "\\subsection*{" $2 "}\n"
}
/cpp/ {
	print("\\begin{verbatim}")
	system("./cut_code.awk < ../code/" $1 " | sed 's/\\t/    /g'")
	print("\\end{verbatim}\n\n")
}
END { print "\\end{document}" }
