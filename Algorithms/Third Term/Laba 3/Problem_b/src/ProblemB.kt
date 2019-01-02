import java.io.*
import java.util.StringTokenizer
import kotlin.system.exitProcess


class PrefixFunction {
    lateinit var reader: FastScanner
    lateinit var writer: PrintWriter

    fun solve() {
        val line = reader.next()
        print(buildPrefixFunction(line).joinToString(" "))
    }

    fun buildPrefixFunction(line: String): MutableList<Int> {
        val prefixFunctionArray = MutableList(line.length) { 0 }
        prefixFunctionArray[0] = 0
        for (i in 1 until line.length) {
            var k = prefixFunctionArray[i - 1]
            while (k > 0 && line[i] != line[k])
                k = prefixFunctionArray[k - 1]
            if (line[i] == line[k])
                ++k
            prefixFunctionArray[i] = k
        }
        return prefixFunctionArray
    }

    fun run() {
        reader = FastScanner(File("input" + ".in"))
        writer = PrintWriter(File("output" + ".out"))

        solve()

        writer.close()
    }

    fun measureTime(name: String, f: () -> Unit) {
        val start = System.nanoTime()
        f()
        println("ProblemB: run for ${(System.nanoTime() - start) / 10e9}")
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
}

fun main(args: Array<String>) {
    PrefixFunction().run()
}