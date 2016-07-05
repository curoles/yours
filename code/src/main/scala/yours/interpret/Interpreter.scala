/* Copyright Igor Lesik 2016
 *
 * English text interpreter.
 */
package yours.interpret

import akka.actor._
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
    inputProcessor(input)
    val actionScript = outputProcessor("todo")
    executor ! actionScript
  }

  def terminate() = {
    actorSystem.terminate()
  }
}
