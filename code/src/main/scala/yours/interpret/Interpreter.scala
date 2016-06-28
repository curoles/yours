/* Copyright Igor Lesik 2016
 *
 * English text interpreter.
 */
package yours.interpret

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

  /** To call like:
    * {{{
    * interpreter(text)
    * }}}
    */
  def apply(input: String) = process(input)

  /** Returns ?
    *
    */
  def process(input: String) = {
    inputProcessor(input)
  }

}
