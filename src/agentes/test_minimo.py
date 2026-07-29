from claude_agent_sdk import query
import asyncio

async def main():
    async for msg in query(prompt="Responde solo con la palabra: funciona"):
        print(msg)

asyncio.run(main())
