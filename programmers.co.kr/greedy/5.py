# https://programmers.co.kr/learn/courses/30/lessons/42861
# Connecting Islands

# This is a Minimum Spanning Tree problem.
# Uses Kruskal's algorithm with union-find.

class UnionFind:
    def __init__(self, n):
        self.n = n
        self.link = list(range(n))
        self.size = [1] * n

    # Returns the representative node
    def find(self, a):
        while (self.link[a] != a):
            a = self.link[a]
        return a

    # Returns True if in same set, False if not
    def same(self, a, b):
        return self.find(a) == self.find(b)

    def union(self, a, b):
        aRep = self.find(a)
        bRep = self.find(b)
        if (self.size[aRep] > self.size[bRep]):
            aRep, bRep = bRep, aRep
        self.link[aRep] = bRep
        self.size[bRep] += self.size[aRep]


def solution(n, costs):
    uf = UnionFind(n)
    costs.sort(key = lambda x: x[2])
    answer = 0
    edgesAdded = 0
    for node1, node2, cost in costs:
        if not uf.same(node1, node2):
            uf.union(node1, node2)
            answer += cost
            edgesAdded += 1
        if edgesAdded == n - 1:
            break

    return answer
