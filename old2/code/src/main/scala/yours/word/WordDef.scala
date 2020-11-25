/* Copyright Igor Lesik 2016
 *
 * Word definition.
 */
package yours.word

import java.nio.file.{Paths, Files}

/** Word definition. '''Y''',,o,,__u__^^r^^''s''
  *
  * [[file:WordDef.scala.html]]
  * 
  */
class WordDef {

  def readXML(path:String) = {
    import scala.xml.XML
    val word = XML.loadFile(path)
    val version = word \ "version"
    println("version "+version.text)
  }
}
