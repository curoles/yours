/* Copyright Igor Lesik 2016
 *
 * English text interpreter.
 */
package yours.interpret

import akka.actor._
import akka.pattern.ask
import akka.util.Timeout
import scala.concurrent.{Await, ExecutionContext, Future}
import scala.concurrent.duration._
import scala.language.postfixOps

import yours.execute.Executor
import yours.execute.ActionScalaScript

/** Interprets user text and then replies and executes commands.
  *
  *
  * <pre class="textdiagram">
  * +---------------+        +-----------------------+       +-------------------+
  * |{io}           |        |                       |       |{io}               |
  * |User Input:Text|        |     Interpreter       |       |Machine Output:Text|
  * |               |        +-----------+-----------+       |                   |
  * |               |        |  Front    |   Back    |       |                   |
  * |               +------->|   End     |   End     +------>|                   |
  * |               |        |           |           |       |                   |
  * |               |        |           |           +---+   |                   |
  * |               |        |cPNK       |cBLU       |   |   |                   |
  * +---------------+        +-----------+-----------+   |   +-------------------+
  *                                      ^               |
  *                                      |               |   +-------------------+
  *                          +-----------------------+   |   |                   |
  *                          |{s}                    |   +-->|  List of commands |
  *                          |     Conversation      |       |                   |
  *                          |                       |       +-------------------+
  *                          |o input/output history |
  *                          |o context              |
  *                          |                       |
  *                          |                       |
  *                          +-----------------------+
  * </pre>
  */
class Interpreter {

  val inputProcessor = new frontend.InputProcessor
  val outputProcessor = new backend.OutputProcessor


  //val executor = new yours.execute.Executor
  val actorSystem = ActorSystem("YoursActorSystem")
  val executor = actorSystem.actorOf(Props[Executor], "executor")

  /** To call like:
    * {{{
    * interpreter(text)
    * }}}
    */
  def apply(input: String) = process(input)

  /** Parses input, then thinks and then acts.
    *
    */
  def process(input: String) = {
    val parsedText = inputProcessor(input)
    val actionScript = outputProcessor(parsedText)
    //executor ! actionScript
    implicit val timeout = Timeout(5 seconds)
    val futureResponse: Future[String] = ask(executor, actionScript)(timeout).mapTo[String]
    val result = Await.result(futureResponse, 5 second)
  }

  def terminate() = {
    actorSystem.terminate()
  }
}
