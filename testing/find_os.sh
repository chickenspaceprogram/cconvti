# finds all tokenizable strings, gets their length, and puts those lengths into token_lengths.txt
# shell scripts are cursed
grep "<os-version>" tokens/8X.xml | sed -e 's/^[ 	]*<os-version>//' | sed -e 's/<\/os-version>$//' | sort -u > os-versions.txt
#sort -nr token_lengths.txt | head -n 1
