#! /usr/bin/env bash
BINWIDTH=50
MIN=0
MAX=200
CHRLIST=( 1 3 5 7 9 11 15 19 )

for i in ${CHRLIST[@]}
do
    if [ -e "chr${i}.test" ]
    then
        echo "File chr${i}.test already exists - skipping"
    else
        $HOME/src/c/bed_tools/frag-size-mm9 chr${i}.bed chr${i} $BINWIDTH $MIN $MAX > "chr${i}.test" 
    fi
done
cat chr*.test > all.test


R --slave <<'R_INPUT_END'
H <- read.table("all.test", sep="|")
colnames(H) <- c("shift", "H", "Chrom")

# normalize each chromosome to it's max
H$norm <- H$H
chromosomes <- unique(H$Chrom)
for (chrom in chromosomes) {
	f <- H$Chrom == chrom
	H$norm[f] <- H$norm[f] / max(H$norm[f])
}

minH <- by(H$H, H$Chrom, min)
for (chrom in names(minH)) {
	print(paste(chrom, ": ", H$shift[H$H==minH[[chrom]]]))
}

library(ggplot2)
pdf("all.test.pdf")
p <- ggplot(data=H, mapping=aes(x=shift, y=norm, col=Chrom)) +
	geom_line(size=1)
print(p)	
dev.off()
R_INPUT_END

open "all.test.pdf"
