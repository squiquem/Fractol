# fract'ol

Infographics project: creating pretty fractals
____

The objective of this project was to explore fractals and generate them graphically. Here is a breakdown of its features:
- 5 basic fractals: Julia, Mandelbrot, Burning Ship, Newton and Tricorn
- You can create an infinity of fractals, adding or removing "heads"
- Moving the mouse around over the Julia fractal udpates one of parameters of the equation and updates it visually
- Pan image with arrow keys
- Zoom and unzoom on mouse
- You can zoom in infinitely, until, of course, the limitations of the CPU are met
- There are a varity of color palettes available
- You can change fractals without restarting the program, by clicking on them
- You can have information about the mouse position.
- Instructions are available
- Multithreading with CPU

## Compile

	make
____

## Run

	./fractol <julia burningship mandelbrot tricorn newton>
____

## Controls

Moving :				<kbd>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;▲&nbsp;</kbd><kbd>&nbsp;▼&nbsp;</kbd><kbd>&nbsp;◄&nbsp;</kbd><kbd>&nbsp;►&nbsp;</kbd><br/>
Iterations (x2):		<kbd>&nbsp;+&nbsp;</kbd><kbd>&nbsp;-&nbsp;</kbd><br/>
Change color:			<kbd>&nbsp;0&nbsp;</kbd><kbd>&nbsp;1&nbsp;</kbd><kbd>&nbsp;2&nbsp;</kbd><kbd>&nbsp;3&nbsp;</kbd><kbd>&nbsp;4&nbsp;</kbd><kbd>&nbsp;5&nbsp;</kbd><kbd>&nbsp;6&nbsp;</kbd><kbd>&nbsp;7&nbsp;</kbd><kbd>&nbsp;8&nbsp;</kbd><kbd>&nbsp;9&nbsp;</kbd> (palette)<br/>
						<kbd>&nbsp;DELETE&nbsp;</kbd> (smooth)<br/>
						<kbd>&nbsp;SUPPR&nbsp;</kbd> (cycles)<br/>
						<kbd>&nbsp;PGUP&nbsp;</kbd><kbd>&nbsp;PGDOWN&nbsp;</kbd> (sharp)<br/>
						<kbd>&nbsp;F1&nbsp;</kbd><kbd>&nbsp;F2&nbsp;</kbd> (heads)<br/>
Restart:				<kbd>&nbsp;ENTER&nbsp;</kbd><br/>
Block Julia parameter:	<kbd>&nbsp;SPACE&nbsp;</kbd><br/>
Zoom:					Mouse wheel or left click<br/>
Infos:					<kbd>&nbsp;F12&nbsp;</kbd><br/>
____

## Screenshots
![Rendu 1](https://github.com/squiquem/fractol/blob/master/screenshots/julia1.PNG)
![Rendu 2](https://github.com/squiquem/fractol/blob/master/screenshots/mandelbrot1.PNG)
![Rendu 3](https://github.com/squiquem/fractol/blob/master/screenshots/julia2.PNG)
![Rendu 4](https://github.com/squiquem/fractol/blob/master/screenshots/mandelbrot2.PNG)
![Rendu 5](https://github.com/squiquem/fractol/blob/master/screenshots/tricorn.PNG)
![Rendu 6](https://github.com/squiquem/fractol/blob/master/screenshots/newton.PNG)
____

If you have any questions or suggestions, feel free to send me an email at squiquem@student.42.fr
