package  
{
	import adobe.utils.CustomActions;
	import net.flashpunk.Entity;
	import net.flashpunk.World;
	import net.flashpunk.FP;
	
	/**
	 * ...
	 * @author Nahuel Lattessi
	 */
	
	public class MainMenu extends World
	{
		[Embed(source = "../assets/PlayGameButton.png")]
		private const PLAYBUTTON_IMG:Class;
		
		private var playButton:Button;
		
		public function MainMenu() 
		{
			//playButton = new Button(playTheGame, null, 48, 395);
			playButton = new Button(playTheGame, null, 150, 250);
			playButton.setSpritemap(PLAYBUTTON_IMG, 312, 22);
			add(playButton);
		}
		
		private function playTheGame():void
		{
			FP.world = new GameWorld();
			destroy();
		}
		
		public function destroy():void
		{
			removeAll();
			playButton = null;
		}
	}

}