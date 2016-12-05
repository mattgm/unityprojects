#3.1
print("3.1 Part (i)")
srs <- rnorm(100, mean = 0, sd = 2);
hist(srs, xlab = "Values")
mu0 = 0
ssd = sd(srs)
n = 100
xbar = mean(srs)
t = (xbar-mu0)/(ssd/sqrt(n))
pval = 2 * pt(t, df=n-1)
alpha = .05
print(paste("pval = ", pval))
if (pval > alpha) {
	print("Failed to reject H0!")
} else {
	print("H0 rejected!")
}

print("")
print("Part (iii)")
rejections = 0
for (i in 1:1000) {
	srs <- rnorm(100, mean = 0, sd = 2);
	mu0 = 0
	ssd = sd(srs)
	n = 100
	xbar = mean(srs)
	t = (xbar-mu0)/(ssd/sqrt(n))
	pval = 2 * pt(t, df=n-1)
	alpha = .05
	
	if (pval < alpha) {
		rejections = rejections + 1
	}
}

proportion = rejections/1000

print(paste("Rejections = ", rejections))
print(paste("Proportion = ", proportion))

print("")
print("Part (iv) with alpha = .01")
rejections = 0
for (i in 1:1000) {
	srs <- rnorm(100, mean = 0, sd = 2);
	mu0 = 0
	ssd = sd(srs)
	n = 100
	xbar = mean(srs)
	t = (xbar-mu0)/(ssd/sqrt(n))
	pval = 2 * pt(t, df=n-1)
	alpha = .01
	
	if (pval < alpha) {
		rejections = rejections + 1
	}
}

proportion = rejections/1000

print(paste("Rejections = ", rejections))
print(paste("Proportion = ", proportion))

print("")
print("Part (iv) with alpha = .1")
rejections = 0
for (i in 1:1000) {
	srs <- rnorm(100, mean = 0, sd = 2);
	mu0 = 0
	ssd = sd(srs)
	n = 100
	xbar = mean(srs)
	t = (xbar-mu0)/(ssd/sqrt(n))
	pval = 2 * pt(t, df=n-1)
	alpha = .01
	
	if (pval < alpha) {
		rejections = rejections + 1
	}
}

proportion = rejections/1000

print(paste("Rejections = ", rejections))
print(paste("Proportion = ", proportion))


#3.2
print("")
print("3.2 Part (i)")
pAM = 26/54
pPM = 22/51
ppool = (26 + 22) / (54 + 51)
SEdp = sqrt(ppool * (1 - ppool) * ((1 / 54) + (1/51)))
z = (pAM - pPM) / SEdp
pval2 = 2 * pnorm(-(abs(z)))
print(paste("P-value = ", pval2))

print("")
print("3.2 Part (ii)")
pClass = ppool
p0 = 0.2
n = 105
z = (pClass - p0) / sqrt((p0 * (1 - p0)) / n)
pval3 = pnorm(-(abs(z)))
print(paste("P-value = ", pval3))


#3.3
print("")
print("3.3")
data <- read.csv(file='p3.csv', sep=',', header=T)
results <- table(data$IceCream, data$Pizza)
#barplot(results, main="Favorite Ice Cream and Pizza",
	#xlab = "Pizza Toppings", ylab = "Favorite Ice Cream Flavor", 
	#xlim=c(0, 5), col=c("blue","red","green"),
	#legend = rownames(results)) 
chisq.test(results)
























