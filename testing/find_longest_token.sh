# finds all tokenizable strings, gets their length, and puts those lengths into token_lengths.txt
# also prints the length of the longest token
# shell scripts are cursed
grep "<accessible>" ../tokens/8X.xml | sed -e 's/^[ 	]*<accessible>//' | sed -e 's/<\/accessible>$//' | awk '{print length}' > token_lengths.txt
sort -nr token_lengths.txt | head -n 1
