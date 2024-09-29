# finds all os versions, sorts them, removes duplicates, and puts the output in os-versions.txt
grep "<os-version>" ../tokens/8X.xml | sed -e 's/^[ 	]*<os-version>//' | sed -e 's/<\/os-version>$//' | sort -u > os-versions.txt
#sort -nr token_lengths.txt | head -n 1
