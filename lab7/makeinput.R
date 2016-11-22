n <- 100
u <- vector()
v <- vector()
w <- vector()
for (i in 0:(n-1)) {
    for (j in 0:(n-1)) {
        if (j - 1 >= 0) {
            u <- c(u, i*n + j)
            v <- c(v, i*n + j - 1)
            w <- c(w, 1)
        }
        if (j + 1 < n) {
            u <- c(u, i*n + j)
            v <- c(v, i*n + j + 1)
            w <- c(w, 1)
        }

        if (i - 1 >= 0) {
            u <- c(u, i*n + j)
            v <- c(v, (i-1)*n + j)
            w <- c(w, 1)
        }
        if (i + 1 < n) {
            u <- c(u, i*n + j)
            v <- c(v, (i+1)*n + j)
            w <- c(w, 1)
        }
    }
}
w <- c(length(u), w)
u <- c(0, u)
v <- c(n*n, v)
m <- matrix(c(u, v, w), ncol = 3)

write.table(m, "dijkstra.in", row.names = F, col.names = F)

g <- graph_from_edgelist(m+1, directed = FALSE)
g <- graph(m, directed = FALSE)
