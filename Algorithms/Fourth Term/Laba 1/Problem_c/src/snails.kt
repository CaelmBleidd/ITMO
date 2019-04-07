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
    var maxFlow = 0
    var s = 1
    var t = 1

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
        s = reader.nextInt()
        t = reader.nextInt()

        for (i in 1..m) {
            val from = reader.nextInt()
            val to = reader.nextInt()
            val capacity = 1

            if (from == to)
                continue

            addEdge(from, to, capacity, false)
        }
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

    }

    data class Edge(val from: Int, val to: Int, val capacity: Int, var flow: Int, val isReversed: Boolean)
}


fun main() {
    val dinic = Dinic()
    dinic.input()
    dinic.findMaxFlow()
    if (dinic.maxFlow < 2)
        println("NO")
    else {
        println("YES")
        val answerForMasha = mutableListOf(dinic.s)
        val answerForPetya = mutableListOf(dinic.s)
        var mashaPos = answerForMasha.first()
        var petyaPos = answerForPetya.first()

        while (mashaPos != dinic.t) {
            for (edgeNumber in dinic.tubes[mashaPos]) {
                if (dinic.edges[edgeNumber].flow == 1) {
                    mashaPos = dinic.edges[edgeNumber].to
                    answerForMasha.add(mashaPos)
                    dinic.edges[edgeNumber].flow = 0
                    break
                }
            }
        }

        while (petyaPos != dinic.t) {
            for (edgeNumber in dinic.tubes[petyaPos]) {
                if (dinic.edges[edgeNumber].flow == 1) {
                    petyaPos = dinic.edges[edgeNumber].to
                    answerForPetya.add(petyaPos)
                    dinic.edges[edgeNumber].flow = 0
                    break
                }
            }
        }

        println(answerForMasha.joinToString(" "))
        println(answerForPetya.joinToString(" "))

    }
}