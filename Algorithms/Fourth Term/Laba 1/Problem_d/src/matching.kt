import java.io.*
import java.lang.Integer.min
import java.lang.Math.abs
import java.util.*


class Dinic {
    lateinit var reader: FastScanner

    val MAX_V = 100000 + 5
    val INF = 1_000_000_000

    val shortestPaths = IntArray(MAX_V) { -1 }
    val deletedV = IntArray(MAX_V) { 0 }

    val tubes = Array<ArrayList<Int>>(MAX_V) { ArrayList() }
    val edges = mutableListOf<Edge>()

    var n = 0
    var m = 0
    var nSize = 0
    var maxFlow = 0
    var s = 1
    var t = 1

    val reachableAndAcceptable = Array(MAX_V) { false }
    val minCutAnswer = hashSetOf<Int>()

    fun addEdge(from: Int, to: Int, capacity: Int, isReversed: Boolean) {
        val firstEdge = Edge(from, to, capacity, 0, isReversed)
        val secondEdge = Edge(to, from, 0, 0, !isReversed)

        tubes[from].add(edges.size)
        edges.add(firstEdge)

        tubes[to].add(edges.size)
        edges.add(secondEdge)
    }

    fun input() {
        reader = FastScanner(File("input" + ".in"))
        n = reader.nextInt()
        m = reader.nextInt()
        nSize = n


        for (i in 1..n) {
            addEdge(0, i, 1, false)

            var to = reader.nextInt()

            while (to != 0) {
                to += n
                addEdge(i, to, 1, false)
                to = reader.nextInt()
            }
        }

        for (i in n + 1 .. m + n) {
            addEdge(i, n + m + 1, 1, false)
        }

        s = 0
        t = n + m + 1
    }

    fun findMaxFlow(): Int {
        while (true) {
            if (!findShortestPaths()) break

            deletedV.fill(0)
            while (true) {
                val pushedFlow = pushFlow(s, INF)
                maxFlow += pushedFlow
                if (pushedFlow == 0)
                    break
            }
        }
        return maxFlow
    }

    fun findShortestPaths(): Boolean {
        shortestPaths.fill(-1)
        val bfsQueue = ArrayDeque<Int>()
        bfsQueue.add(s)
        shortestPaths[s] = 0

        while (bfsQueue.isNotEmpty()) {
            val v = bfsQueue.poll()
            for (toEdgeNumber in tubes[v]) {
                val edge = edges[toEdgeNumber]

                if (shortestPaths[edge.to] == -1 && edge.flow < edge.capacity) {
                    shortestPaths[edge.to] = shortestPaths[v] + 1
                    bfsQueue.add(edge.to)
                }
            }
        }
        return shortestPaths[t] != -1
    }

    fun pushFlow(v: Int, flow: Int): Int {
        if (flow == 0) return 0
        if (v == t) return flow

        for (to in deletedV[v] until tubes[v].size) {
            val id = tubes[v][deletedV[v]]
            val toEdge = edges[id].to

            if (shortestPaths[toEdge] != shortestPaths[v] + 1) {
                deletedV[v]++
                continue
            }
            val pushed = pushFlow(toEdge, min(flow, edges[id].capacity - edges[id].flow))
            if (pushed > 0) {
                edges[id].flow += pushed
                edges[id xor 1].flow -= pushed
                return pushed
            }

            deletedV[v]++
        }
        return 0
    }

    fun solve() {
        findMaxFlow()
    }

    fun printMaxFlow() {
        println(maxFlow)
        for (edgeIndex in 0 until edges.size step 4) {
            val realEdges = edges.subList(edgeIndex, edgeIndex + 4)
            var flow = edges[edgeIndex].flow
            var isReversed = edges[edgeIndex].isReversed
            for (edge in realEdges) {
                if (abs(flow) < abs(edge.flow)) {
                    flow = edge.flow
                    isReversed = edge.isReversed
                }
            }
            println(if (isReversed) flow * (-1) else flow)
        }
    }

    fun run() {
        input()
        solve()
    }

    fun measureTime(executing: String, f: () -> Unit) {
        val start = System.nanoTime()
        f()
        println(executing + ": run for ${(System.nanoTime() - start) / 10e9}")
    }


    inner class FastScanner(file: File) {
        var br: BufferedReader = BufferedReader(InputStreamReader(System.`in`))
        var st: StringTokenizer? = null

        fun next(): String {
            while (st == null || !st!!.hasMoreTokens()) {
                st = StringTokenizer(br.readLine())
            }
            return st!!.nextToken()
        }

        fun nextInt(): Int {
            return next().toInt()
        }

        fun nextLong(): Long {
            return next().toLong()
        }

        fun nextDouble(): Double {
            return next().toDouble()
        }
    }

    fun bfsMinCut(vertex: Int) {
        reachableAndAcceptable[vertex] = true
        for (edge in tubes[vertex])
            if (!reachableAndAcceptable[edges[edge].to] && edges[edge].flow < edges[edge].capacity)
                bfsMinCut(edges[edge].to)

    }

    fun findMinCut() {
        bfsMinCut(s)
        for (edgeNumber in 0 until edges.size step 4) {
            if (reachableAndAcceptable[edges[edgeNumber].from] && !reachableAndAcceptable[edges[edgeNumber].to]
                    || !reachableAndAcceptable[edges[edgeNumber].from] && reachableAndAcceptable[edges[edgeNumber].to]) {
                minCutAnswer.add(edgeNumber / 4 + edgeNumber % 4 + 1)
            }
        }
    }

    fun printAnswerMinCut() {
        println("${minCutAnswer.size} $maxFlow")
        println(minCutAnswer.sorted().joinToString(" "))
    }

    data class Edge(val from: Int, val to: Int, val capacity: Int, var flow: Int, val isReversed: Boolean)
}

fun main() {
    val dinic = Dinic()
    dinic.input()
    dinic.findMaxFlow()
    println(dinic.maxFlow)

    for (i in 1..dinic.n) {
        for (edges in dinic.tubes[i]) {
            if (dinic.edges[edges].flow > 0) {
                println("${dinic.edges[edges].from} ${dinic.edges[edges].to - dinic.n}")
                break
            }
        }
    }
}