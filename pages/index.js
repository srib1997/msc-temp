import { useEffect } from 'react'

var datas = {
  uv: '',
  temp: '',
  humidity: '',
  wind: ''
}

var timer

function HomePage() {
  useEffect(() => {
    fetchAll()
    timer = setInterval(fetchAll, 5000)
    return () => {
      clearInterval(timer);
    }
  }, [])

  const fetchAll = async() => {
    try{
      const response = await fetch(`/api/all`, { method: 'POST'})
  
      const result = await response.json()

      console.log(result)
      console.log('sgkvl')
    }catch (e){
      console.log(e)
    }
  }

  return <div>{JSON.stringify(datas)}</div>
}

export default HomePage
