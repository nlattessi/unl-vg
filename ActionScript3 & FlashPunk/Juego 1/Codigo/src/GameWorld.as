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
		private var cuadro1:Cuadro1;
		private var cuadro2:Cuadro2;
		private var wall:Wall;
		private var portal:Portal;
		private var portalInf:Number = 0;
		private var portalSup:Number = 0;
		
		public function GameWorld() 
		{
			var i:uint;
			
			//Pongo al jugador
			this.cuadro1 = new Cuadro1(20,27);
			this.add(cuadro1);
			
			//Pongo el piso y suelo
			for (i = 0; i < 20; i++)
			{
				this.add(new Wall(i, 0));
				this.add(new Wall(i, 14));
			}
			//Pongo los portales iniciales y le paso las ubicaciones
			//al jugador
			do
			{
				portalInf = FP.rand(20);
			}
			while (portalInf == 11)			
			portalSup = FP.rand(20);
			add(new Portal(portalSup, 0));
			add(new Portal(portalInf, 14));
			//cuadro1.setPortalInf(this.portalInf);
			cuadro1.portalInf = this.portalInf;
			cuadro1.portalSup = this.portalSup;
			//cuadro1.setPortalSup(this.portalSup);
		
			//Pongo los items a recoger
			for (i = 0; i < 5; i++)
			{
				this.add(new Cuadro2(FP.rand(39), FP.rand(23) + 2));
			}
		}
		
		override public function update():void
		{
			var i:uint;
			FP.randomizeSeed();
			
			//Repongo items si no hay
			if (classCount(Cuadro2) == 0)
			{
				for (i = 0; i < 5; i++)
				{
					this.add(new Cuadro2(FP.rand(39), FP.rand(23) + 2));
				}	
			}
			
			//Agrego enemigos para que siempre haya al menos 2
			if (classCount(Enemy) < 2)
			{
				for (i = 0; i < 2; i++)
				{
					this.add(new Enemy(0, FP.rand(24) + 2));
				}
			}
			
			super.update();
		}		
	}

}