package  
{
	import net.flashpunk.Entity;
	import net.flashpunk.graphics.Text;
	
	/**
	 * ...
	 * @author Nahuel Lattessi
	 */
	
	public class GameScore extends Entity
	{
		public var score:int;
		
		public function GameScore() 
		{
			graphic = new Text("Puntos: 0");
			score = 0;
		}
		
		public function addScore():void
		{
			score += 1;
			Text(graphic).text = "Puntos: " + score.toString();
		}
		
		public function removeScore():void
		{
			score -= 1;
			Text(graphic).text = "Puntos: " + score.toString();
		}
		
		public function getScore():uint
		{
			return score;
		}
	}

}