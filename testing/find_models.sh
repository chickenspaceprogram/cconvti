# finds all tokenizable strings, gets their length, and puts those lengths into token_lengths.txt
# shell scripts are cursed
grep "<model>" ../tokens/8X.xml | sed -e 's/^[ 	]*<model>//' | sed -e 's/<\/model>$//' | sort -u > models.txt
#sort -nr token_lengths.txt | head -n 1
