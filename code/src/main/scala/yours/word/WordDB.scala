/* Copyright Igor Lesik 2016
 *
 * This file contains WordDB API in form of an abstract class.
 */
package yours.word

/** Defines API to Word DB.
  * 
  */
abstract class WordDB(val path:String) {

  /** Open and initialize */
  def open(): Boolean

  /** Returns True if word exists in DB.*/
  def exists(word:String): Boolean

  /** Find word */
  def find(word:String): Option[String]
}

