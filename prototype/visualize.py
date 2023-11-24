import tkinter as tk
import numpy as np
import random

def run_visualization(folded_form, clear_vis = True):
    window = tk.Tk()
    window.title("Folded Shape")

    canvas = tk.Canvas(window, width=800, height=800)
    canvas.pack()

    def draw_polygon(canvas, points, outline_color = 'white', clear_vis = True):
        scale = lambda x: 600 * (x) + 100
        jitter = np.random.randn() * 3 # to help visualize distinct polygons if edges overlap
        transform = lambda x: scale(x) + (jitter if not clear_vis else 0)
        
        new_points = []
        for px, py in points:
            new_points += [transform(px), transform(py)]
        
        canvas.create_polygon(new_points, outline=outline_color, fill='', width=0.1)

    tkinter_colors = [
        "white", "red", "green", "blue", "cyan", "yellow",
        "orange", "purple", "pink",
        "#FF0000", "#00FF00", "#0000FF", "#FFFF00", "#FF00FF", "#00FFFF", "#FFA07A"
    ]

    for polygon in folded_form:
        color = random.choice(tkinter_colors)
        draw_polygon(canvas, polygon.vertices, outline_color=color, clear_vis=clear_vis)
    window.mainloop()