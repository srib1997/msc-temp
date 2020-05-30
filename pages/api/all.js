const db = require('../../knex/knex.js')

export default async (req, res) => {
  if (req.method === 'POST') {
    // Process a POST request
    try {
      const result = await db('uv_sensor').orderBy('created_at', 'desc')

      return res.json({
        success: true,
        result
      })
    } catch (error) {
      console.log(error)
    }
  } else {
    // Handle any other HTTP method
    return res.json({
      success: false,
    })
  }
}