package  
{
	import net.flashpunk.World;
	import net.flashpunk.FP;
	
	/**
	 * ...
	 * @author Nahuel Lattessi
	 */
	
	public class GameWorld extends World
	{
		//private var player:Player;
		public static var player:Player;
		public static var gameScore:GameScore;
		private var maxRedEnemy:uint;
		private var maxGreenEnemy:uint;
		private var time:Number = 0;
		
		public function GameWorld() 
		{
			player = new Player;
			add(player);
			addRedEnemy();
			// FP.rand(384) + 64
			gameScore = new GameScore();
			gameScore.x = 290;
			gameScore.y = 450;
			add(gameScore);
			maxRedEnemy = 5;
			maxGreenEnemy = 5;
			time = 0;
		}
		
		override public function update():void
		{
			super.update();
			
			time += FP.elapsed;
			
			if (time > 5)
			{
				time = 0;
				maxRedEnemy += FP.rand(5);
				maxGreenEnemy += FP.rand(5);
			}
			
			if (classCount(RedEnemy) < maxRedEnemy)
			{
				addRedEnemy();
			}
			
			if (classCount(GreenEnemy) < maxGreenEnemy)
			{
				addGreenEnemy();
			}
			
			if (gameScore.score < 0)
			{				
				endTheGame();
			}
		}
		
		private function addRedEnemy():void
		{
			var side:uint = FP.rand(2);
			if (side == 0)
				add(new RedEnemy(0, FP.rand(416) + 32));
			else
				add(new RedEnemy(608, FP.rand(416) + 32));
		}
		
		private function addGreenEnemy():void
		{
			var side:uint = FP.rand(2);
			if (side == 0)
				add(new GreenEnemy(FP.rand(576) + 32, 0));
			else
				add(new GreenEnemy(FP.rand(576) + 32, 448));
		}
		
		public function endTheGame():void
		{
			removeAll();
			FP.world = new MainMenu();
		}
	}

}