import tkinter as tk
import json
import numpy as np
import random

def run_visualization(folded_form, clear_vis = True):
    window = tk.Tk()
    window.title("Folded Shape")

    canvas = tk.Canvas(window, width=800, height=800)
    canvas.pack()

    def draw_polygon(canvas, points, outline_color = 'white', clear_vis = True):
        scale = lambda x: 600 * (x) + 100
        jitter = np.random.randn() * 4 # to help visualize distinct polygons if edges overlap
        transform = lambda x: scale(x) + (jitter if not clear_vis else 0)
        
        new_points = []
        for px, py in points:
            new_points += [transform(px), transform(py)]
        
        canvas.create_polygon(new_points, outline=outline_color, fill='', width=0.1)

    tkinter_colors = [
        "white", "red", "green", "cyan", "yellow",
        "orange", "purple", "pink",
        "#FF0000", "#00FF00", "#0000FF", "#FFFF00", "#FF00FF", "#00FFFF", "#FFA07A"
    ]
    # tkinter_colors = ['white']

    for polygon_points in folded_form:
        color = random.choice(tkinter_colors)
        draw_polygon(canvas, polygon_points, outline_color=color, clear_vis=clear_vis)
    window.mainloop()


def get_form(filepath):
    with open(filepath, "r") as f:
        polygons = json.load(f)
    
    folded_form = []
    for polygon_id in polygons:
        polygon = []
        for vertex_id in polygons[polygon_id]:
            vertex = polygons[polygon_id][vertex_id]
            polygon.append((vertex["x"], vertex["y"]))
        
        folded_form.append(polygon)
    return folded_form

if __name__ == "__main__":
    filepath = "out.json"
    folded_form = get_form(filepath)
    run_visualization(folded_form, clear_vis=True)
    # run_visualization(folded_form, clear_vis=False)