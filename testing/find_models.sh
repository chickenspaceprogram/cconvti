# finds all calculator models, sorts them, filters for unique ones, and puts the output in models.txt
grep "<model>" ../tokens/8X.xml | sed -e 's/^[ 	]*<model>//' | sed -e 's/<\/model>$//' | sort -u > models.txt
#sort -nr token_lengths.txt | head -n 1
