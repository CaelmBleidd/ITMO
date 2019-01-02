import java.io.*
import java.util.*

class ProblemA {
    lateinit var input: FastScanner
    lateinit var output: PrintWriter

    fun run() {
        input = FastScanner(File("schedule.in"))
        output = PrintWriter(File("schedule.out"))

        solve()

        output.close()
    }

    private fun solve() {
        val n = input.nextLong()
        val list = TreeSet<Task>(Comparator { first, second ->
            when {
                first.deadline > second.deadline -> 1
                else -> -1
            }
        })
        var result: Long = 0

        for (i in 0 until n) {
            val task = Task(deadline = input.nextLong(), cost = input.nextLong(), overdue = false)
            list.add(task)
        }

        val tmpTask = TreeSet<Task>(Comparator { first, second ->
            when {
                first.cost > second.cost -> 1
                else -> -1
            }
        })

        var time = 1L
        val resultList = mutableListOf<Task>()

        for (i in list) {
            if (i.deadline == 0L) {
                resultList.add(i)
                continue
            }
            tmpTask.add(i)
            if (i.deadline >= time) {
                time += 1
            } else {
                resultList.add(tmpTask.first())
                tmpTask.pollFirst()
            }
        }
        resultList.forEach { result += it.cost }
        output.print(result)

    }

    inner class FastScanner(file: File) {
        var br: BufferedReader = BufferedReader(FileReader(file))
        var st: StringTokenizer? = null

        fun next(): String {
            while (st == null || !st!!.hasMoreTokens()) {
                st = StringTokenizer(br.readLine())
            }
            return st!!.nextToken()
        }

        fun nextLong() = next().toLong()

    }

    data class Task(val deadline: Long, val cost: Long, var overdue: Boolean)
}

fun main(args: Array<String>) {
    ProblemA().run()
}