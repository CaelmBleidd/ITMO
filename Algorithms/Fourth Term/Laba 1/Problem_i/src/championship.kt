import java.io.*
import java.lang.Integer.min
import java.lang.Math.abs
import java.util.*
import kotlin.math.max


class Dinic {
    private lateinit var reader: FastScanner

    private val MAX_V = 100 + 5
    private val INF = 1_000_000_000

    private val shortestPaths = IntArray(MAX_V) { -1 }
    private val deletedV = IntArray(MAX_V) { 0 }

    private val tubes = Array<ArrayList<Int>>(MAX_V) { ArrayList() }
    private val edges = mutableListOf<Edge>()

    private var n = 0
    private var m = 0
    private var maxFlow = 0
    private var s = 1
    private var t = 1

    private val scoreTable = Array(MAX_V) { MutableList(MAX_V) { '.' } }
    private val scores = MutableList(MAX_V) { 0 }
    private val shouldPlay = MutableList(MAX_V) { mutableListOf<Int>() }
    private val expected = MutableList(MAX_V) { 0 }

    private fun addEdge(from: Int, to: Int, capacity: Int, isReversed: Boolean) {
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

        for (i in 1..n) {
            val line = reader.next()
            for (char in line.withIndex()) {
                scoreTable[i][char.index + 1] = char.value
                when (char.value) {
                    'W' -> scores[i] += 3
                    'w' -> scores[i] += 2
                    'l' -> scores[i] += 1
                    'L' -> scores[i] += 0
                    '.' -> shouldPlay[i].add(char.index + 1)
                }
            }
        }

        for (i in 1..n) {
            expected[i] = max(0, reader.nextInt() - scores[i])
        }

        s = 0
        t = n + 1

        for (i in 1..n) {
            addEdge(i, t, expected[i], false)
        }

        for (i in 1..n) {
            addEdge(s, i, canGet(i), false)
        }

        for (i in 1..n) {
            for (j in shouldPlay[i]) {
                if (j > i) {
                    addEdge(i, j, 3, false)
                }
            }
        }

    }

    private fun canGet(team: Int): Int {
        var count = 0
        for (i in shouldPlay[team]) {
            if (i > team) {
                count += 3
            }
        }
        return count
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

    private fun findShortestPaths(): Boolean {
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

    private fun pushFlow(v: Int, flow: Int): Int {
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

    private fun solve() {
        findMaxFlow()
    }

    private fun printMaxFlow() {
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

    fun output() {
        for (i in 1..n) {
            for (edgeNumber in tubes[i]) {
                var edge = edges[edgeNumber]
                if (edge.to != t && edge.from != s && edge.to != s && i < edge.to) {
                    when (edge.flow) {
                        0 -> {
                            scoreTable[i][edge.to] = 'W'
                            scoreTable[edge.to][i] = 'L'
                        }
                        1 -> {
                            scoreTable[i][edge.to] = 'w'
                            scoreTable[edge.to][i] = 'l'
                        }
                        2 -> {
                            scoreTable[i][edge.to] = 'l'
                            scoreTable[edge.to][i] = 'w'
                        }
                        3 -> {
                            scoreTable[i][edge.to] = 'L'
                            scoreTable[edge.to][i] = 'W'
                        }
                    }
                }
            }
        }

        for (i in 1..n) {
            scoreTable[i].subList(1, n + 1).forEach { print(it) }
            println()
        }
    }

    data class Edge(val from: Int, val to: Int, val capacity: Int, var flow: Int, val isReversed: Boolean)
}

fun main() {
    val dinic = Dinic()
    dinic.input()
    dinic.findMaxFlow()
    dinic.output()
}