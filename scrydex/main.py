from fastapi import FastAPI
from fastapi.responses import HTMLResponse
from engine import get_pokemon_from_query
from pokemon import create_database_from_csv

app = FastAPI()
ALL_POKEMON = create_database_from_csv()
MAX_RESULTS = 100

@app.get("/search")
async def search(query: str = ""):
    valid_pokemon = get_pokemon_from_query(ALL_POKEMON, query)
    results = [p.serialized() for p in valid_pokemon]
    
    return {
        "count": len(valid_pokemon),
        "results": [p.serialized() for p in valid_pokemon]
    }
    
@app.get("/", response_class=HTMLResponse)
async def homepage() -> str:
    s = ""
    with open("homepage.html", "r") as file:
        for line in file:
            s += line
    return s