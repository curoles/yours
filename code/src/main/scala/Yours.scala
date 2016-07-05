import yours._

/** Yours command line app.
  *
  * [[file:htmlsrc/Yours.scala.html]]
  */
object Yours extends App {

  println(Console.BLUE+"YOURS Operating User Reactive System by Igor Lesik"+Console.RESET)
  println("Arguments: " + (args mkString ", "))

  val interpreter = new yours.interpret.Interpreter

  println("YOURS is ready and listening.")

  if (args.length > 0) {
    readLineLoop()
  }
  else {
    //interpreter("Hello Igor, number 1 super-hero. How are you?")
    interpreter("hello.")
  }

  interpreter.terminate()

  def readLineLoop() = {
    var userInput:String = null;
    do {
      userInput = scala.io.StdIn.readLine(">")
      if (userInput != null) {
        interpreter(userInput)
        println()
      }
    } while (userInput != null)
    println()
  }
}

