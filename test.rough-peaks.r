library(ggplot2)

quartz()

d <- read.table("temp", sep="|")
colnames(d) <- c("start", "end", "val", "strand", "island")
d$strand <- factor(d$strand)

# length distribution of rough peaks
ilen <- ddply(d, c("island", "strand"), 
	summarise,
		len=max(end) - min(start))
p <- ggplot(ilen) + 
	geom_histogram(aes(x=len), binwidth=100) +
	facet_wrap(~strand)
print(p)

# mid points of each peak
d$mid <- (d$start + d$end)/2

# plot some peaks on + and - strand
d$val2 <- d$val
minus_filter <- d$strand == '-'
d$val2[minus_filter] <- d$val2[minus_filter]*-1

dp <- d[d$start >= 8*5000000 & d$end < 9*5000000,]
p <- ggplot(dp) +
	geom_linerange(aes(x=mid, ymin=0, ymax=val2, col=strand))
print(p)	


